#!/usr/bin/env sh

rootfolder=/nfs/hn46/xiaolonw/cnncode/caffe-3dnormal_r_n
sourcefolder=/nfs/ladoga_no_backups/users/xiaolonw/seg_cls/sliding_window_edge_high_test

GLOG_logtostderr=1 $rootfolder/build_balaton/examples/3dnormal/convert_normal_win_high_5_test.bin $sourcefolder/images/ $sourcefolder/locs/testLoc1.txt  $sourcefolder/leveldb_fusetest/3d_test_5new_db1 0 0 55 55   $sourcefolder/testpatches_coarselayout/reg_coarselay_tri_test/   $sourcefolder/reg_localedge_tri/  $sourcefolder/testpatches_coarselayout/reg_coarse_van_tri/  $sourcefolder/reg_edges/  $sourcefolder/reg_layout_coarse/ 

