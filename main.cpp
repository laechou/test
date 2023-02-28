#include <iostream>
#include <Eigen/Eigen>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

struct orb
{
	int lel;
	float x,y;
	int angle_x,angle_y;
	int id;//==0: orb pt; >0: lk pt
	int des[32];
};

int compareorb() {
	string path="/home/lae/projects/Test/data/fpga_orb/";
	FILE *fp=fopen("/home/lae/projects/Test/data/fpga_orb/t.txt","r");
	char fl[100];
	while(-1!=fscanf(fp,"%s",fl))
	{
		string orb_fg_name=path+"Cam0_Orb_fpga/"+fl;
		string orb_pc_name=path+"Cam0_Orb_pc/"+fl;
		ifstream f1;
		f1.open(orb_fg_name.c_str());
		if(!f1.is_open()) {
			printf("cannot open %s\n",orb_fg_name.c_str());
			continue; }

		std::cout<<"Processing "<<orb_fg_name<<" ...."<<std::endl;
		int num=0;int ts;int i;
		f1>>num;f1>>ts;f1>>i;

		std::map<int,orb> orbs_fg;
		while(!f1.eof())
		{
			orb ob;
			f1>>ob.lel;f1>>ob.angle_x;f1>>ob.angle_y;
			f1>>ob.x;f1>>ob.y;f1>>ob.id;
			for (int j = 0; j < 32; ++j) {
				f1>>ob.des[j];
			}
			orbs_fg.insert(make_pair(ob.angle_x,ob));
		}
		f1.close();

		num=100;
		f1.open(orb_pc_name.c_str());
		f1>>num;f1>>ts;f1>>i;

		std::map<int,orb> orbs_pc;
		while(!f1.eof())
		{
			orb ob;
			f1>>ob.lel;f1>>ob.angle_x;f1>>ob.angle_y;
			f1>>ob.x;f1>>ob.y;f1>>ob.id;
			for (int j = 0; j < 32; ++j) {
				f1>>ob.des[j];
			}
			orbs_pc.insert(make_pair(ob.angle_x,ob));
		}
		f1.close();

		//compare two files
		//first method: save file by order
		string save_orb_fp=path+"Cam0_Orb_fpga/order/order_"+fl;
		string save_orb_pc=path+"Cam0_Orb_pc/order/order_"+fl;

		FILE *fp=fopen(save_orb_fp.c_str(),"w");
		for(auto &it : orbs_fg)
		{
			fprintf(fp,"%d %d %d %.3f %.3f %d ",
					it.second.lel,it.second.angle_x,it.second.angle_y,
					it.second.x,it.second.y,it.second.id);
			for (int j = 0; j < 32; ++j) {
				fprintf(fp,"%d ",it.second.des[j]);
			}
			fprintf(fp,"\n");
		}
		fclose(fp);

		fp=fopen(save_orb_pc.c_str(),"w");
		for(auto &it : orbs_pc)
		{
			fprintf(fp,"%d %d %d %.3f %.3f %d ",
					it.second.lel,it.second.angle_x,it.second.angle_y,
					it.second.x,it.second.y,it.second.id);
			for (int j = 0; j < 32; ++j) {
				fprintf(fp,"%d ",it.second.des[j]);
			}
			fprintf(fp,"\n");
		}
		fclose(fp);

	}
	fclose(fp);

	printf("over!\n");
	return 0;
}

int main()
{
	//test 2
	compareorb();
	return 0;
}