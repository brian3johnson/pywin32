# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here.
import pathlib
import sys

sys.path.insert(0, pathlib.Path(__file__).parents[2].resolve().as_posix())

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = "pywin32"
copyright = "2022, Mark Hammond"
author = "Mark Hammond"
release = "305"

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ["sphinx.ext.autodoc", "sphinx.ext.todo"]

templates_path = ["_templates"]
exclude_patterns = []

rst_prolog = """
.. |Pythonwin| replace:: :program:`Pythonwin`
.. |Scintilla| replace:: :program:`Scintilla`
.. _Scintilla: http://www.scintilla.org/
"""

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "alabaster"
html_static_path = ["_static"]
html_sidebars = {
    "**": [
        "about.html",
        "localtoc.html",
        "navigation.html",
        "searchbox.html",
    ]
}

# -- Options for alabaster theme----------------------------------------------
# https://alabaster.readthedocs.io/en/latest/customization.html

html_theme_options = {
    "logo_name": True,
    "description": "Python wrapper for the Windows API",
    "github_user": "mhammond",
    "github_repo": "pywin32",
    "github_banner": False,
    "github_button": True,
    "github_type": "star",
    "badge_branch": "main",
    "show_powered_by": True,
}

# -- Options for Sphinx autodoc extension ------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/autodoc.html#configuration

autodoc_mock_imports = [
    "win32api",
    "pywintypes",
    "win32com",
    "pythoncom",
    "winerror",
    "win32file",
    "win32security",
    "win32event",
]

# -- Options for Sphinx todo extension ---------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/todo.html#configuration

todo_include_todos = True
# todo_emit_warnings = True
# todo_link_only = True
