#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n

GLOG_logtostderr=1 $rootfolder/build/examples/3dnormal/convert_normal_functest.bin /home/xiaolonw/affordance/cls4/   /home/xiaolonw/affordance/cls4/trainLabels_sel.txt  /home/xiaolonw/affordance/leveldb/3d_test_db_small_ran 0 0 55 55