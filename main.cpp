#include <iostream>
#include "Huffman.h"

int main() {
	string s1;
	string s2;
	while(true)
	{
		cout<<"1.ѹ��"<<endl;
		cout<<"2.��ѹ"<<endl;
		cout<<"3.�˳�"<<endl;
		int o;
		cin>>o;
		if(o==1)
		{
			huffman h;
			cout<<"��������Ҫѹ�����ļ�"<<endl;
			cin>>s1;		
			cout<<"������ѹ���ļ���Ŀ���ַ"<<endl;
			cin>>s2; 
			h.zip(s1,s2);
		}
		else if(o==2)
		{
			huffman h;
			cout<<"��������Ҫ��ѹ���ļ�"<<endl;
			cin>>s1;
			cout<<"�Ƿ��ѹ����ǰ�ļ��� y/n"<<endl;
			string ss;
			cin>>ss;
			if(ss == "y") h.unzip(s1,"");	
			else
			{
				string s2;
				cout<<"�����ѹ��Ŀ���ļ���"<<endl;
				cin>>s2;
				h.unzip(s1,s2);	
			}
		} 
		else 
		{
			cout<<"�ɹ��˳�"<<endl;
			system("pause");
		}
	}
	return 0;
}
