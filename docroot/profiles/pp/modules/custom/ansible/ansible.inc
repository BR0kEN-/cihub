<?php

require_once __DIR__ . '/../../../vendor/autoload.php';

$manager = new Ko\ProcessManager();
$manager->demonize();

$process = $manager->fork(function (Ko\Process $p) {
  $p->setProcessTitle('drupal-ansible');

  $result = NULL;
  $exit_code = NULL;

  // > /dev/null 2>&1
//  exec(sprintf('ansible-playbook -vvvv -i %s/inventory %s/playbook.yml --limit=matrix', __DIR__, __DIR__), $result, $exit_code);
//  print_r($result);
  sleep(10);
  exit($exit_code);
});

$process->onSuccess(function () {
  file_put_contents(__DIR__ . '/0.txt', '');
});

$process->onError(function () {
  file_put_contents(__DIR__ . '/1.txt', '');
});

$process->wait();
