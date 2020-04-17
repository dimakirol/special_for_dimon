#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <gumbo.h>
static void search_for_links(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

GumboAttribute* href;
if (node->v.element.tag == GUMBO_TAG_A &&
(href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
std::cout << href->value << std::endl;
}

GumboVector* children = &node->v.element.children;
for (unsigned int i = 0; i < children->length; ++i) {
search_for_links(static_cast<GumboNode*>(children->data[i]));
}

}

int main() {
    try {
        std::ifstream in("index.html");
        std::string contents;
        try {
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
        } catch (...){ std::cout << "Vse huyna!";}

        GumboOutput *output = gumbo_parse(contents.c_str());
        search_for_links(output->root);
        gumbo_destroy_output(&kGumboDefaultOptions, output);
    }catch(...){
        std::cout << "Debili BLYAT!!!!!!!!!";
    }
}