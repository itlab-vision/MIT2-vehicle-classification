#!/usr/bin/env sh

BIN=../../bin

GLOG_logtostderr=1 $BIN/train_net.exe mlp_solver_ldb.prototxt 