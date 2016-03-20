# Set this to the root of your project when deployed:
css_dir = "css"
sass_dir = "scss"
fonts_dir = "fonts"
images_dir = "images"
javascripts_dir = "js"

# You can select your preferred output style here (can be overridden via the command line):
# Values: ":expanded", ":nested", ":compact" or ":compressed"
output_style = :compressed

# To enable relative paths to assets via compass helper functions.
relative_assets = true

# To disable debugging comments that display the original location of your selectors.
line_comments = false

# If you prefer the indented syntax, you might want to regenerate this
# project again passing --syntax sass, or you can uncomment this:
# preferred_syntax = :sass
# and then run:
# sass-convert -R --from scss --to sass sass scss && rm -rf sass && mv scss sass

# If you prefer the indented syntax, you might want to regenerate this
# project again passing --syntax sass, or you can uncomment this:
# preferred_syntax = :sass
# and then run:
# sass-convert -R --from scss --to sass scss scss && rm -rf sass && mv scss sass
preferred_syntax = :scss

begin
  require "autoprefixer-rails"
  puts "SCSS compiles with Autoprefixer."

  on_stylesheet_saved do |file|
    css = File.read(file)
    map = file + ".map"

    if File.exists? map
      result = AutoprefixerRails.process(css,
        to: file,
        from: file,
        map: {
          prev: File.read(map),
          inline: false
        }
      )

      File.open(file, "w") { |io| io << result.css }
      File.open(map,  "w") { |io| io << result.map }
    else
      File.open(file, "w") { |io| io << AutoprefixerRails.process(css) }
    end
  end
rescue LoadError
  puts "SCSS compiles without Autoprefixer."
end
