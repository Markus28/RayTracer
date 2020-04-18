import subprocess
from setuptools import setup
from distutils.command.install import install as original_install

class install(original_install):
    def run(self):
        subprocess.call(['cmake', 'RayTracer/src'])
        subprocess.call(['make'])
        subprocess.call(['mv', 'libRayTracer.so', 'RayTracer'])
        super().run()

setup(
    name='RayTracer',
    version='0.0',
    description='A CPU RayTracer',
    author='Markus28',
    packages=['RayTracer'],
    cmdclass={'install': install},
    package_data={'RayTracer': ["libRayTracer.so"]}
)
