============
Installation
============

.. contents::
   :depth: 1
   :local:

Overview
========

|pywin32| only supports the Windows operating system 😉 and Python ≥ 3.6. `Release 228`_ is the last to support Python 2. :ref:`binary_releases` are deprecated.

.. _Release 228: https://github.com/mhammond/pywin32/releases/tag/b228

.. todo::

   * Add commentary about using Virtual Environments.
   * Add commentary about whether |pywin32| works from WSL2.

.. _install_with_pypi:

PyPI
====

Install |pywin32| from `PyPI`_ with :program:`pip` from the :program:`Command Prompt` or :program:`Windows PowerShell`:

.. _PyPI: https://pypi.org/project/pywin32/

.. code-block:: console

   ❯ python -m pip install --upgrade pywin32

.. _execute_pywin32_postinstall:

   If you encounter any problems when upgrading (e.g., "module not found" errors), execute:

.. code-block:: console

   ❯ python Scripts/pywin32_postinstall.py -install

This will make some small attempts to cleanup older conflicting installs.

.. note::

   To use |pywin32| for system-wide features, such as registering |com| objects or implementing Windows Services, run :file:`pywin32_postinstall.py` from an elevated command prompt (i.e., "Run as Administrator").

Build from source
=================

Building from source requires `Visual Studio`_ and the `Windows SDK`_. Some free compilers probably work but have not been tested. Let me know your experiences!

.. _Visual Studio: https://visualstudio.microsoft.com/
.. _Windows SDK: https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/

Install using :file:`setup.py`:

.. code-block:: console

   ❯ python setup.py install

or

.. code-block:: console

   ❯ python setup.py --help

You can run :file:`setup.py` without any arguments to see specific information about dependencies. A vanilla MSVC installation should be able to build most extensions and list any extensions that could not be built due to missing libraries. If the build actually fails with your configuration, please `open an issue <https://github.com/mhammond/pywin32/issues>`_.

Pre-release builds
==================

For unreleased changes, download builds made by `GitHub Actions <https://github.com/mhammond/pywin32/actions/>`_:

* Choose any "workflow" from the **main** branch
* Download its "artifacts"

.. _binary_releases:

Binary releases
===============

.. deprecated:: 305

   Install from :ref:`install_with_pypi` instead. See `Release 305`_ notes.

.. _Release 305: https://github.com/mhammond/pywin32/releases/tag/b305

|pywin32| traditionally offered :file:`pywin32.exe` files for installation. This is going to stop soon.

Support for building :file:`pywin32.exe` installers was `removed from setuptools <https://github.com/pypa/distutils/pull/170>`_. At some point in the future they cannot be provided.

While they are still provided, find them on `GitHub <https://github.com/mhammond/pywin32/releases>`_.

Run as a Windows Service
========================

Modern Python installers do not, by default, install Python in a way that is suitable for running as a service, particularly for other users.

Ensure Python is installed in a location where the user running the service has access to the installation and is able to load :file:`pywintypesXX.dll` and :file:`pythonXX.dll`.

Manually copy :file:`pythonservice.exe` from the :file:`site-packages\win32` directory to the same place as these DLL files.

Troubleshooting
===============

A very common report is that people install |pywin32|, but many imports fail with errors similar to "The specified procedure could not be found" or "Entry-point not found".

In almost all cases, this tends to mean there are other |pywin32| DLLs installed in your system but in a different location than the new ones. This sometimes happens in environments that ship with |pywin32| (e.g., `Anaconda`_).

.. _Anaconda: https://www.anaconda.com/

The possible solutions are:

* Run the :ref:`pywin32_postinstall.py <execute_pywin32_postinstall>` script documented above.
* Find and remove all other copies of :file:`pywintypes{XX}.dll` and :file:`pythoncom{XX}.dll` (where :samp:`{XX}` is the Python version (e.g., :samp:`39` for Python 3.9).