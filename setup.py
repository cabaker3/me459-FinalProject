from setuptools import setup, find_packages

setup(
    name='mamt tool',
    author='Caitlin Baker',
    author_email='cabaker3@wisc.edu',
    version="1.0.1",
    packages = find_packages(),
    description='Calculating maintenance task time',
    install_requires=[
        'pandas',
        'datetime',
        'timeit',
    ]
)
