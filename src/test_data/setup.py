from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'test_data'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'msg'), glob('test_data/msg/*.msg')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='amwhisper',
    maintainer_email='3056422950@qq.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "test_data = test_data.test_data:main",
        ],
    },
)
