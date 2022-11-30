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

show_authors = True

rst_prolog = """
.. |pywin32| replace:: **pywin32**
.. |Pythonwin| replace:: :program:`Pythonwin`
.. |Scintilla| replace:: :program:`Scintilla`
.. _Scintilla: http://www.scintilla.org/
.. _Windows API: https://learn.microsoft.com/en-us/windows/win32/
.. |isapi| replace:: :abbr:`ISAPI (Internet Server Application Programming Interface)`
.. _isapi_filters: https://learn.microsoft.com/en-us/previous-versions/iis/6.0-sdk/ms525103(v=vs.90)
.. _isapi_extensions: https://learn.microsoft.com/en-us/previous-versions/iis/6.0-sdk/ms525282(v=vs.90)
.. |adodbapi| replace:: ADO DB-API
.. |ado| replace:: :abbr:`ADO (ActiveX Data Objects)`
.. _Microsoft ActiveX Data Objects (ADO): https://learn.microsoft.com/en-us/sql/ado/
.. |com| replace:: :abbr:`COM (Component Object Model)`
.. _Component Object Model (COM): https://learn.microsoft.com/en-us/windows/win32/com/
.. |iis| replace:: :abbr:`IIS (Internet Information Services)`
.. _Microsoft Internet Information Services (IIS): https://learn.microsoft.com/en-us/iis/
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
    "description": "Python for Windows Extensions",
    "fixed_sidebar": False,
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
