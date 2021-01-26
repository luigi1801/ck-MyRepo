#
# Collective Knowledge (individual environment - setup)
#
# See CK LICENSE.txt for licensing details
# See CK COPYRIGHT.txt for copyright details
#
# Developer: Grigori Fursin, Grigori.Fursin@cTuning.org, http://fursin.net
#

import os

##############################################################################
# setup environment

def setup(i):

    s=''

    cus=i['customize']
    env=i['env']


    # Get paths
    fp=cus['full_path']
    ep=cus['env_prefix']
    #print(i)

    
    dir_lib=os.path.dirname(fp)
    #pl=os.path.join(pb,'lib')
    env[ep]=fp
    #env[ep+'_LIB']=pl

    return {'return':0, 'bat':s}
