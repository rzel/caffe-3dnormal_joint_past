/*#include <cuda_runtime.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>*/

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include <leveldb/db.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "caffe/caffe.hpp"
#include "caffe/util/io.hpp"

#include <string>
#include <fstream>

using namespace std;
using namespace cv;
using namespace caffe;
using std::vector;



int CreateDir(const char *sPathName, int beg) {
	char DirName[256];
	strcpy(DirName, sPathName);
	int i, len = strlen(DirName);
	if (DirName[len - 1] != '/')
		strcat(DirName, "/");

	len = strlen(DirName);

	for (i = beg; i < len; i++) {
		if (DirName[i] == '/') {
			DirName[i] = 0;
			if (access(DirName, 0) != 0) {
				CHECK(mkdir(DirName, 0755) == 0)<< "Failed to create folder "<< sPathName;
			}
			DirName[i] = '/';
		}
	}

	return 0;
}

char buf[101000];
int main(int argc, char** argv)
{

	Caffe::set_phase(Caffe::TEST);
	//Caffe::SetDevice(0);
	//Caffe::set_mode(Caffe::CPU);

	if (argc == 8 && strcmp(argv[7], "CPU") == 0) {
		LOG(ERROR) << "Using CPU";
		Caffe::set_mode(Caffe::CPU);
	} else {
		LOG(ERROR) << "Using GPU";
		Caffe::set_mode(Caffe::GPU);
	}


	Caffe::set_mode(Caffe::GPU);
	Caffe::SetDevice(0);

	NetParameter test_net_param;
	ReadProtoFromTextFile(argv[1], &test_net_param);
	Net<float> caffe_test_net(test_net_param);
	NetParameter trained_net_param;
	ReadProtoFromBinaryFile(argv[2], &trained_net_param);
	caffe_test_net.CopyTrainedLayersFrom(trained_net_param);

	//vector<shared_ptr<Layer<float> > > layers = caffe_test_net.layers();
	//const DataLayer<float> *datalayer = dynamic_cast<const DataLayer<float>* >(layers[0].get());
	//CHECK(datalayer);

	string labelFile(argv[3]);
	int data_counts = 0;
	FILE * file = fopen(labelFile.c_str(), "r");
	while(fgets(buf,100000,file) > 0)
	{
		data_counts++;
	}
	fclose(file);

	vector<Blob<float>*> dummy_blob_input_vec;
	string rootfolder(argv[4]);
	rootfolder.append("/");
	CreateDir(rootfolder.c_str(), rootfolder.size() - 1);
	string folder;
	string fName;

	float output;
	int counts = 0;

	file = fopen(labelFile.c_str(), "r");

	Blob<float>* c1 = (*(caffe_test_net.bottom_vecs().rbegin()))[0];
    int c2 = c1->num();
	int batchCount = std::ceil(data_counts / (floor)(c2));//(test_net_param.layers(0).layer().batchsize()));//                (test_net_param.layers(0).layer().batchsize() ));

	string resulttxt = rootfolder + "videoResult.txt";
	FILE * resultfile = fopen(resulttxt.c_str(), "w");

	float accuracy = 0;

	for (int batch_id = 0; batch_id < batchCount; ++batch_id)
	{
		LOG(INFO)<< "processing batch :" << batch_id+1 << "/" << batchCount <<"...";
		const vector<Blob<float>*>& result = caffe_test_net.Forward(dummy_blob_input_vec);
		Blob<float>* bboxs = (*(caffe_test_net.top_vecs().rbegin()))[0];
		int bsize = bboxs->num();

		for (int i = 0; i < bsize && counts < data_counts; i++, counts++)
		{
			char fname[1010];
			int id;
			fscanf(file, "%s", fname);
			fscanf(file, "%d", &id);

			fprintf(resultfile, "%s %d ", fname, id);
			int channels = bboxs->channels();
			float maxval = -1;
			int maxid = -1;

			for (int c = 0; c < channels; c ++)
			{
				fprintf(resultfile, "%f ",  (float)(bboxs->data_at(i, c, 0, 0)) );
				if(maxval <  (float)(bboxs->data_at(i, c, 0, 0)) )
				{
					maxval = (float)(bboxs->data_at(i, c, 0, 0));
					maxid = c;
				}
			}
			fprintf(resultfile, "\n");
			if (maxid == id)
			{
				accuracy += 1;
			}

		}
	}


	fclose(resultfile);
	fclose(file);

	accuracy /= data_counts;

	printf("%f\n", accuracy);


	return 0;
}
