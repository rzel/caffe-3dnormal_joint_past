#!/usr/bin/env sh                                                                                                

# test_net_seg.bin test_proto pre_train_model label.txt outputfolder [CPU/GPU]

ROOTFILE=/home/dragon123/3dnormal_joint_cnncode/caffe-3dnormal_joint

GLOG_logtostderr=1  /home/dragon123/3dnormal_joint_cnncode/caffe-3dnormal_joint_past/build/tools/test_net_3dnormal_locimtxts.bin seg_test_2fc_3dnormal_all.prototxt /home/dragon123/3dnormal_joint_cnncode/models/fusion_model_all/3dnormal__iter_240000  /home/dragon123/3dnormal_joint_cnncode/imgfile_fusion_2.txt /home/dragon123/3dnormal_joint_cnncode/slide_results/txts_fusion_2






