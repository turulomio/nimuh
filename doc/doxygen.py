import os
f=open("../CMakeLists.txt")
f.readline()
__version__=f.readline().split(' VERSION ')[1][:-2]
f.close()
print(__version__)
os.system("""sed -i -e "41d" Doxyfile""")#Delete line 41
os.system("""sed -i -e "41iPROJECT_NUMBER         = {}" Doxyfile""".format(__version__))#Insert line 41
os.system("""doxygen Doxyfile""")
os.system("""rsync -avzP -e 'ssh -l turulomio' html/ frs.sourceforge.net:/home/users/t/tu/turulomio/userweb/htdocs/doxygen/nimuh/ --delete-after""")
