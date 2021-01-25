from distutils.core import setup, Extension

hello_world_module = Extension('hello_module',
                           sources = ['hello_module.c']
						   , extra_compile_args=['-DMS_WIN64'])

setup(name = 'lesson_one',
      version = '1.0',
      description = 'Python Package with Hello World C Extension',
      ext_modules = [hello_world_module],

      url='http://adamlamers.com',
      author='Adam Lamers',
      author_email='adamlamers at gmail dot com')