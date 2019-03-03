This is a procedure to make a new release:
1) Change version in CMakeLists.txt
2) Add Changelog in README.md
3) git commit -am "nimuh-version"
4) git push
 ) Update doxygen
5) Create a new tag in Github
6) Update ebuild for Gentoo
7) Move to windows and follow install instructions
8) Compress dist directory and upload to Github release
