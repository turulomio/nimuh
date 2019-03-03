This is a procedure to make a new release:
1) git checkout master
2) git pull
3) Change version in CMakeLists.txt
4) Add Changelog in README.md
5) git commit -am "nimuh-version"
6) git push
7) Update doxygen
8) Create a new tag in Github
9) Update ebuild for Gentoo
10) Move to windows and follow install instructions
11) Compress dist directory and upload to Github release
