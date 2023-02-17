#include <iostream>
#include "Huffman.h"

int main() {
	string s1;
	string s2;
	while(true)
	{
		cout<<"1.压缩"<<endl;
		cout<<"2.解压"<<endl;
		cout<<"3.退出"<<endl;
		int o;
		cin>>o;
		if(o==1)
		{
			huffman h;
			cout<<"请输入所要压缩的文件"<<endl;
			cin>>s1;		
			cout<<"请输入压缩文件的目标地址"<<endl;
			cin>>s2; 
			h.zip(s1,s2);
		}
		else if(o==2)
		{
			huffman h;
			cout<<"请输入所要解压的文件"<<endl;
			cin>>s1;
			cout<<"是否解压到当前文件夹 y/n"<<endl;
			string ss;
			cin>>ss;
			if(ss == "y") h.unzip(s1,"");	
			else
			{
				string s2;
				cout<<"输入解压的目标文件夹"<<endl;
				cin>>s2;
				h.unzip(s1,s2);	
			}
		} 
		else 
		{
			cout<<"成功退出"<<endl;
			system("pause");
		}
	}
	return 0;
}
