#!/usr/bin/env php
<?php

require_once __DIR__ . '/../../../vendor/autoload.php';

$climate = new League\CLImate\CLImate();
$climate->arguments->add([
  'PLAYBOOK' => [
    'prefix' => 'p',
    'required' => TRUE,
    'longPrefix' => 'playbook',
    'description'  => 'Ansible playbook',
  ],
  'INVENTORY' => [
    'prefix' => 'i',
    'required' => TRUE,
    'longPrefix' => 'inventory-file',
    'description'  => 'File with hosts list',
  ],
  'SUBSET' => [
    'prefix' => 'l',
    'longPrefix' => 'limit',
    'description'  => 'Limit of hosts to run playbook',
    'defaultValue' => 'all',
  ],
]);

try {
  $climate->arguments->parse($argv);
}
catch (\Exception $e) {
  $climate->backgroundRed($e->getMessage());
  exit(13);
}

$options = $climate->arguments->toArray();
$manager = new Ko\ProcessManager();

$manager->demonize();

$process = $manager->fork(function (Ko\Process $p) use ($options) {
  $p->setProcessTitle('ansible-provision');

  $output = NULL;
  $return_var = NULL;

  exec(
    sprintf('ansible-playbook -l %s -i %s %s &', $options['SUBSET'], $options['INVENTORY'], $options['PLAYBOOK']),
    $output,
    $return_var
  );

  exit($return_var);
});

$process->onSuccess(function () {
  define('DRUPAL_ROOT', getcwd());

  require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
  drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);

  // @todo Extend database column and set status of provisioning.
  file_put_contents(__DIR__ . '/0.txt', var_export(db_select('node', 'n')->fields('n')->execute()->fetchAll(), TRUE));
});

$process->onError(function () {
  file_put_contents(__DIR__ . '/1.txt', '');
});

$process->wait();
