# -------------------------------------------
# Global configuration of the mat2doc system
# -------------------------------------------

# When writing this file, certain variables are already defined:
#
#   self.root points to the project directory


import localconf

conf=ConfType()

def mycopyrightfun(self):
    vf=file(self.root+'ltfat_version');
    v=vf.readline()
    vf.close
    
    f=file(self.root+'mat2doc/copyrightplate')
    buf=f.readlines()
    f.close

    copyright=['Copyright (C) 2005-2012 Peter L. Soendergaard.\n','This file is part of LTFAT version '+v]
    copyright.extend(buf)
    
    return copyright

conf.copyright=mycopyrightfun

contentsfiles=['Contents','gabor/Contents','fourier/Contents',
               'filterbank/Contents','nonstatgab/Contents',
               'frames/Contents',
               'sigproc/Contents','auditory/Contents',
               'demos/Contents','signals/Contents']

# ------------------------------------------
# Configuration of PHP for Sourceforge
# ------------------------------------------

php=PhpConf()

php.indexfiles=contentsfiles

php.includedir='../include/'

php.urlbase='doc/'


# ------------------------------------------
# Local php
# ------------------------------------------

phplocal=PhpConf()

phplocal.indexfiles=contentsfiles

phplocal.includedir='../include/'

phplocal.urlbase='doc/'


# ------------------------------------------
# Configuration of LaTeX
# ------------------------------------------

tex=TexConf()

tex.indexfiles=contentsfiles
tex.urlbase='http://ltfat.sourceforge.net/doc/'
    
# ------------------------------------------
# Configuration of Matlab
# ------------------------------------------

mat=MatConf()
mat.urlbase='http://ltfat.sourceforge.net/doc/'

# ------------------------------------------
# Configuration of Verification system
# ------------------------------------------

verify=ConfType()

verify.basetype='verify'

verify.targets=['AUTHOR','TESTING','REFERENCE']

verify.notappears=['FIXME','BUG','XXL','XXX']

verify.ignore=["demo_","comp_","assert_","Contents.m","init.m"]



