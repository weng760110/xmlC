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


static void
parseDoc (char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr cur;
	xmlChar *propName;
	xmlChar *propLen;
	xmlChar *text;

	char Buffer[256];
	/*char replaceText[1240];*/

	memset(Buffer, 0x00, sizeof(Buffer));
	/*memset(replaceText, 0x00, sizeof(replaceText));*/

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

    cur = root->xmlChildrenNode;
    while (cur != NULL) {
		memset(Buffer, 0x00, sizeof(Buffer));

        if (xmlStrcmp(cur->name, (const xmlChar *)"text") == 0) {
        	cur = cur->next;
			continue;
		}
		propName = xmlGetProp(cur, "name");
		propLen = xmlGetProp(cur, "len");
		if ((propName != NULL) ) {
			text = xmlNodeListGetString(doc, cur->xmlChildrenNode, 0);
			if (text != NULL) {
        		if (xmlStrcmp(cur->name, (const xmlChar*)"char") == 0) {
					if (propLen != NULL &&
						atoi(propLen) > 0) {
						sprintf(Buffer, "%s  %s[%d] = \"%s\";", 
								cur->name, 
								propName,
								atoi(propLen),
								text);
					}
					else {
						sprintf(Buffer, "%s  %s = %s;", 
								cur->name, 
								propName,
								text);
					}
				}
				else if ((xmlStrcmp(cur->name, (const xmlChar*)"int") == 0) ||
						(xmlStrcmp(cur->name, (const xmlChar*)"long") == 0) ||
						(xmlStrcmp(cur->name, (const xmlChar*)"ulong") == 0)) {
					if (propLen != NULL &&
						atoi(propLen) > 0) {
						sprintf(Buffer, "%s  %s[%d] = {%s};", 
								cur->name, 
								propName,
								atoi(propLen),
								text);
					}
					else {
						sprintf(Buffer, "%s  %s = %d;", 
								cur->name, 
								propName,
								atoi(text));
					}
				}
				else {
					if (propLen != NULL &&
						atoi(propLen) > 0) {
						sprintf(Buffer, "%s  %s[%d] = \"%s\";", 
								cur->name, 
								propName,
								atoi(propLen),
								text);
					}
					else {
						sprintf(Buffer, "%s  %s = %s;", 
								cur->name, 
								propName,
								text);
					}
				}
				xmlFree(text);
			}
			else {
				sprintf(Buffer, "%s  %s", 
						cur->name, 
						propName,
						text);
			}
        	xmlFree(propName);
        	xmlFree(propLen);

			if (Buffer[0] != 0 &&
		   	 	Buffer[1] != 0) {
				printf("%s\n", Buffer);
			}
		}
		else {
			if (propName == NULL) {
        		die("Name is NULL!!!\n");
			} 
			else {
				xmlFree(propName);
			}
			if (cur->name == NULL) {
        		die("Type is NULL!!!\n");
			}
			if (propLen == NULL) {
        		die("Len is NULL!!!\n");
			}
			else {
				xmlFree(propLen);
			}
			break;
		}

        cur = cur->next;
    }

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
