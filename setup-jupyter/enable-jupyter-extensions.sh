# enable jupyter extensions

jupyter contrib nbextension install --user --symlink
jupyter nbextensions_configurator enable --user

# setup the notebook extensions to the ones that I want active
jupyter contrib nbextension install --user
jupyter nbextension enable equation-numbering/main
jupyter nbextension enable execute_time/ExecuteTime
jupyter nbextension enable spellchecker/main
jupyter nbextension enable toggle_all_line_numbers/main
jupyter nbextension enable equation-numbering/main
jupyter nbextension enable highlighter/highlighter
jupyter nbextension enable ruler/main
jupyter nbextension enable ruler/edit
jupyter nbextension enable collapsible_headings/main

jupyter nbextension enable varInspector/main
# RUN jupyter nbextension enable hinterland/hinterland
jupyter nbextension enable toc2/main
jupyter nbextension enable datestamper/main
jupyter nbextension enable code_prettify/code_prettify


