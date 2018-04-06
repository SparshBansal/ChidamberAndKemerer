#include "c_and_k.h"

// constructor
c_and_k::c_and_k()
{
	this->package_list.clear();
	this->class_map.clear();
	this->graph.clear();

	this->console = spd::get("console");
}

// getter method
std::vector<Class_Information_Package*> c_and_k::get_package_list()
{
	return this->package_list;
}

// setter method
void c_and_k::set_package_list(std::vector<Class_Information_Package*> package_list)
{
	this->package_list = package_list;
}


void c_and_k::_init_()
{
	if (this->package_list.empty())
	{
		this->console->warn("Package list empty");
		return;
	}

	// populate the class map
	this->class_map.clear();
	
	for (Class_Information_Package* package : this->package_list)
		if (class_map.find(package->get_id()) == class_map.end())
			class_map.insert({package->get_id(), package->get_name()});

	this->graph.resize(class_map.size());
	this->indegree.resize(class_map.size());
	this->outdegree.resize(class_map.size());

	std::fill(indegree.begin(), indegree.end(),0);
	std::fill(outdegree.begin(), outdegree.end(),0);

	// construct the class graph
	for (Class_Information_Package* package : this->package_list)
		for (int parent : package->get_parents())
		{
			graph[parent].push_back(package->get_id());
			indegree[package->get_id()]++;
			outdegree[parent]++;
		}

}


double* c_and_k::compute_metrics()
{
	int depth_tree = this->depth_of_inheritance_tree();
	this->console->info("Depth of inheritance tree : {}", depth_tree);
	this->number_of_children();
	this->weighted_method_count();
	this->coupling_between_objects();
	this->response_for_class();
	return NULL;
}

int c_and_k::_dfs(int root, int visited[])
{
	console->info("_dfs on {} : " , root);
	visited[root]=1;
	int height=-1;
	for (int i = 0; i < graph[root].size(); ++i){
		if(!visited[graph[root][i]]) height=std::max(height,_dfs(graph[root][i],visited));
	}
	return height+1;
}


// depth of inheritance tree is the max of the depth 
// of the inheritance tree , we can get that by running 
// dfs on the graph
double c_and_k::depth_of_inheritance_tree()
{
	// get depth of inheritance tree using dfs
	int visited[class_map.size()];
	std::fill(visited, visited + class_map.size(), 0);
	int height = -1;
	for (int i=0; i<graph.size(); i++)
	{
		if (!indegree[i])
			height = std::max(height,_dfs(i, visited));
	}
	return height;
}

// number of children is the number of immediate subclasses
// of a class , we can get that using the outdegree measure 
// each node in class graph
double c_and_k::number_of_children()
{
	// use graph to find number of children for each class
	for (int i=0; i<outdegree.size(); i++)
		console->info("class {} , noc  {} " , class_map[i], outdegree[i]);
}



// weighted method count is simply the number of methods in the 
// class , we can conviniently get this using the method set 
// availaible in the Class_information_package
double c_and_k::weighted_method_count()
{
	for (Class_Information_Package* package : package_list)
	{
		console->info("WMC for class {} ; {} " , class_map[package->get_id()] , package->get_methods_set().size());
	}
}

// coupling between objects is the number of other classes a 
// class is coupled with , this can be computed by iterating 
// and maintaing a set of classes it interacts with using the 
// objects in the sets maintained in Class_information_package
double c_and_k::coupling_between_objects()
{
	for (Class_Information_Package* package : package_list)
	{
		std::unordered_set<int> class_set;
		std::vector<int> data_accessess = package->get_data_accesses();
		std::vector<int> out_method_calls = package->get_out_method_calls();

		for (int data_access: data_accessess)
			class_set.insert(data_access);
		for (int method_call: out_method_calls)
			class_set.insert(method_call);

		console->info("Class {} : CBO : {}", class_map[package->get_id()], class_set.size());
		class_set.clear();
	}
}


double c_and_k::response_for_class()
{
	for (Class_Information_Package* package : package_list)
	{
		// sum of remote methods + class methods
		int mc = package->get_methods_set().size();
		std::set<int> rm(package->get_out_method_calls().begin(), package->get_out_method_calls().end());
		console->info("Class : {} , RFC : {}" , class_map[package->get_id()], mc + rm.size());
	}
}
