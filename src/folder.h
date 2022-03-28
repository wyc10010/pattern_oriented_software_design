#ifndef FOLDER_H
#define FOLDER_H

#include <list>

#include "node.h"
#include "node_iterator.h"
#include "iterator.h"
#include "visitor.h"

class Folder : public Node {
public:
    Folder(std::string id, std::string name, double size = 0):Node(id,name,size) {
        _id = id;
        _name = name;
        _size = size;
    }

    std::string id() const {
        return _id;
    }

    std::string name() const {
        return _name;
    }
    

    void updatePath(std::string path) override {
        _path = path;
        Iterator *it = createIterator();
        for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->updatePath(route());
        }
    }

    std::string route() const override {
        return _path + "/" + _name;
    }

    double size() const override {
        double _size = 0;
        std::list<Node *>::const_iterator ptr;
        for(ptr = _nodes.begin(); ptr != _nodes.end(); ptr++) {
            _size += (*ptr)->size();
        }
        return _size;
    }

    void addNode(Node* node) override {
        _nodes.push_back(node);
        node->updatePath(route());
    }

    Node* getNodeById(std::string id) const override {
        std::list<Node *>::const_iterator ptr;
        for(ptr = _nodes.begin(); ptr != _nodes.end(); ptr++) {
            if((*ptr)->id() == id) {
                return (*ptr);
            }
            try {
                return (*ptr)->getNodeById(id);
            } catch(std::string e) {}
        } 
        throw (std::string("Expected get node but node not found."));
    }
    
    void deleteNodeById(std::string id) override {
        std::list<Node *>::iterator ptr;
        for(ptr = _nodes.begin(); ptr != _nodes.end();ptr++) {
            if((*ptr)->id() == id) {
                _nodes.erase(ptr);
                return;
            }
            try {
                (*ptr)->deleteNodeById(id);
                return;
            } catch(std::string e) {}
        }
        throw (std::string("Expected delete node but node not found."));
    }

    Iterator * createIterator() const override {
        return new NodeIterator<std::list<Node *>::const_iterator>(_nodes.begin(), _nodes.end());
    }

    void accept(Visitor *visitor) override {
        visitor->visitFolder(this);
    }
    
    void addNodes(std::list<Node*> nodes) override {
        std::list<Node *>::const_iterator ptr;
        for(ptr = nodes.begin(); ptr != nodes.end(); ptr++) {
            _nodes.push_back((*ptr));
            (*ptr)->updatePath(route());
        }
    }

    std::list<Node *> getData() {
        return _nodes;
    }

private:
    std::list<Node *> _nodes;
    std::string _id, _name, _path , _str;
    double _size;
};



#endif