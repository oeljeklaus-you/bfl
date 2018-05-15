#include<iostream>
using namespace std;
void test();
int main()
{
	int a=32;
	for (int i = 0; i < 11; ++i)
	{
		cout<<"第"<<i+1<<"次调用:"<<endl;
		test();
	}
	cout<<(a>>5)<<endl;
	return 0;
}
void test()
{
	static int c = 0,r=rand();
	cout<<c<<endl;
	if(c>4)
	{
		c=0;
		r=rand();
	}
	c++;
	
	cout<<r<<endl;
}


void cal_excp_and_cross_arr(){
        reach_flag = (int *)calloc((nodes.size() + 1), sizeof(int));
        int *exit_flag = (int *)calloc((nodes.size() + 1), sizeof(int));
        querycnt = -1;
        //bool flag;
        for(int i = TopoOrder.size() - 1; i >= 0; i--){
            int u = TopoOrder[i];
            //u的新id
            int u_newID = nodeLabel1[u].oldID_mapto_newID;
            
            querycnt += 2;
            int sz = excpID_O[u].size();
            //int cnt = 0;
            //用于判断异常点
            for(int n = 0; n < sz; n ++){
                int newID = nodeLabel1[excpID_O[u][n]].oldID_mapto_newID;
                if(nodeLabel2[u_newID].interval < nodeLabel2[newID].interval /*&& exit_flag[newID] != querycnt*/){
                    nodeLabel2[u_newID].excpID.push_back(newID);
                    exit_flag[newID] = querycnt;
                }
            }
            
            for(int j=0; j<nodes[u].N_O_SZ; j++){
                //子节点
                int addr = nodes[u].N_O[j];
                //子节点新id
                int addr_newID = nodeLabel1[addr].oldID_mapto_newID;
                int len = id_cross_arr_pro[u_newID].size();
                if(nodeLabel2[addr_newID].rlt == nodeLabel2[u_newID].rlt) {
                    //excpID
                    sz = nodeLabel2[addr_newID].excpID.size();
                    //将判断子节点的异常点是否是父节点异常点，如果是添加，如果不是，不处理
                    for(int n = 0; n < sz; n ++){
                        if(nodeLabel2[u_newID].interval < nodeLabel2[nodeLabel2[addr_newID].excpID[n]].interval &&
                           exit_flag[nodeLabel2[addr_newID].excpID[n]] != querycnt){
                            nodeLabel2[u_newID].excpID.push_back(nodeLabel2[addr_newID].excpID[n]);
                            exit_flag[nodeLabel2[addr_newID].excpID[n]] = querycnt;
                        }
                    }
                    sz = nodeLabel2[addr_newID].id_cross_arr.size();
                    //int len = id_cross_arr_pro[u].size();
                    for(int n = 0; n < sz; n ++){
                        if(exit_flag[nodeLabel2[addr_newID].id_cross_arr[n]] == querycnt + 1 ||
                           reach_flag[nodeLabel2[addr_newID].id_cross_arr[n]] == querycnt)
                            continue;
                        
                        if(!is_reachable(u_newID, nodeLabel2[addr_newID].id_cross_arr[n], len)){
                            
                            id_cross_arr_pro[u_newID].push_back(nodeLabel2[addr_newID].id_cross_arr[n]);
                            exit_flag[nodeLabel2[addr_newID].id_cross_arr[n]] = querycnt + 1;
                        }
                    }
                }
                else {
                    if(exit_flag[addr_newID] != querycnt + 1 && reach_flag[addr_newID] != querycnt &&
                       !is_reachable(u_newID, addr_newID, len)){
                        id_cross_arr_pro[u_newID].push_back(addr_newID);
                        exit_flag[addr_newID] = querycnt + 1;
                    }
                }
            }
            
            sz = id_cross_arr_pro[u_newID].size();
            for(int j = 0; j < sz; j ++){
                if(reach_flag[id_cross_arr_pro[u_newID][j]] != querycnt)
                    nodeLabel2[u_newID].id_cross_arr.push_back(id_cross_arr_pro[u_newID][j]);
            }
            if(nodeLabel2[u_newID].id_cross_arr.size() > 0)
                sort(nodeLabel2[u_newID].id_cross_arr.begin(), nodeLabel2[u_newID].id_cross_arr.end());//, cmpNewID);
            if(nodeLabel2[u_newID].excpID.size() > 0)
                sort(nodeLabel2[u_newID].excpID.begin(), nodeLabel2[u_newID].excpID.end());//, cmpNewID);
        }
        
        
    }