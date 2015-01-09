# MIT2-vehicle-classification

###Short description

This project is developed at Nizhny Novgorod State University (CMC faculty, ITLab laboratory).

Project maintainers:

- [Valentina Kustikova](https://github.com/valentina-kustikova)
- [Pavel Druzhkov](https://github.com/druzhkov-paul)


Project structure:
- "MIT2_converters->scripts" contains MATLAB-scripts to convert [MIT2 data]( http://people.csail.mit.edu/xiaoxuma/proj/vehi_reco/index_vehi_reco.htm) to the set of bmp-images
- "MIT2_converters->prepare_mit2" contains a solution for Visual Studio 2010, application provides some preprocessing MIT2 data for the next classification using deep neural networks
- "mit2_caffe_models->mit2" contains DNNs and results for MIT2 data, models for 4 vehicle classes (car, van, sedan, taxi)
- "mit2_caffe_models->mit2_carvan" contains DNNs and results for MIT2 data, models (.prototxt files) for 2 vehicle classes (car, van)
- "mit2_caffe_models->mit2_sedantaxi" contains DNNs and results for MIT2 data, models (.prototxt files) for 2 vehicle classes (sedan, taxi)

[Overall results](https://docs.google.com/spreadsheets/d/1Ws0j148Zw43TI8jMbsLBFyxuqxfAXfan4OiKnAlkzEM/edit?usp=sharing)