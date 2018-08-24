#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

void die(char *msg)
{
  fprintf(stderr, "%s", msg);
  return;
}

/*
void
parseNode (xmlDocPtr doc, xmlNodePtr cur, char *subchild)
{

    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)subchild)))
        {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

            printf("%s\n", key);
            xmlFree(key);
        }
        cur = cur->next;
    }
    return;
}
*/

static void
parseDoc (char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr cur;
	xmlChar *rootPropName;
	xmlChar *propName;
	xmlChar *propCount;

	char Buffer[256];

    doc = xmlParseFile(docname);

    if (doc == NULL ) {
        die("Document parsing failed. \n");
		return;
    }

    root = xmlDocGetRootElement(doc); //Gets the root element of the XML Doc

    if (root == NULL) {
        xmlFreeDoc(doc);
        die("Document is Empty!!!\n");
		return;
    }

	printf("typedef %s {\n", root->name);
	rootPropName = xmlGetProp(root, "name");

    cur = root->xmlChildrenNode;
    while (cur != NULL) {
		memset(Buffer, 0x00, sizeof(Buffer));

		if (memcmp(cur->name, "text", 4) == 0) {
        	cur = cur->next;
			continue;
		}
		propName = xmlGetProp(cur, "name");
		if (propName != NULL) {
			propCount = xmlGetProp(cur, "count");
			if (propCount != NULL) {
				sprintf(Buffer, "\t%s %s[%s];", 
						cur->name, 
						propName, 
						propCount);
				xmlFree(propCount);
			}
			else {
				sprintf(Buffer, "\t%s %s;", 
						cur->name, 
						propName);
			}
        	xmlFree(propName);
		}

		if (Buffer[0] != 0 &&
		    Buffer[1] != 0) {
			printf("%s\n", Buffer);
		}

        cur = cur->next;
    }

	printf("} %s;\n", rootPropName);
    xmlFree(rootPropName);

    xmlFreeDoc(doc);
    return;
}

int
main(int argc, char **argv)
{
    char *docname;

    if (argc != 2) {
        printf("Usage: %s <docname>\n", argv[0]);
        return(0);
    }

    docname = argv[1];

    parseDoc (docname);

    return (1);
}

