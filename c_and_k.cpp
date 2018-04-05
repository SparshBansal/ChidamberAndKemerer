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

double c_and_k::number_of_children()
{
	// use graph to find number of children for each class
	for (int i=0; i<outdegree.size(); i++)
		console->info("class {} , noc  {} " , class_map[i], outdegree[i]);
}

double c_and_k::weighted_method_count()
{
	for (Class_Information_Package* package : package_list)
	{
		console->info("WMC for class {} ; {} " , class_map[package->get_id()] , package->get_methods_set().size());
	}
}
