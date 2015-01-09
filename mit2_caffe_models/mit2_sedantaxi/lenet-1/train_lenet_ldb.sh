#!/usr/bin/env sh

BIN=../../bin

GLOG_logtostderr=1 $BIN/train_net.exe lenet_solver_ldb.prototxt
