# Uncrustify code formatter

## For terminal users
There is a script `uncrustify.sh` that can be used to format the code with uncrustify directly from the terminal. Just cd into devtools/formatter and run `./uncrustify.sh`. Code formatting changes can be done with a pre commit hook. 

## For VSCode users
There is an uncrustify extension for VSCode that can be used to format the code. The settings for the extension are stored in the `.vscode/settings.json` file. The settings for uncrustify are stored in the `uncrustify.cfg` file. Everything should be setup correctly, if not chek whether VSCode accepted the wokspace settings and check the uncrustify paths in VSCode settings. Uncrustify has to be installed on the system and be in the path.

## Install uncrustify on macOS with homebrew

`brew install uncrustify`
