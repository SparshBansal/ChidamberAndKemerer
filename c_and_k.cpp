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
		if (class_map.find(package->get_name()) == class_map.end())
			class_map.insert({package->get_name(), package->get_id()});

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
	
	return NULL;
}


double c_and_k::depth_of_inheritance_tree()
{
	// construct
	return NULL;
}
