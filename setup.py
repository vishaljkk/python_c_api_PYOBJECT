from distutils.core import setup, Extension

module = Extension('exmod',include_dirs=['/usr/local/inculde'],libraries = ['pthread'], sources=['exmodmodule.c'])

setup(name='exmod',version ='1.0',description='This is an example package',author='vkk',ext_modules=[module])