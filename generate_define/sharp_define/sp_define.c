#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "pub_str_api.h"

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
    xmlChar *propType;
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
        propType = xmlGetProp(cur, "type");
        propLen = xmlGetProp(cur, "len");
        if ((propName != NULL) &&
            (propType != NULL) &&
            (propLen != NULL)) {
            text = xmlNodeListGetString(doc, cur->xmlChildrenNode, 0);
            if (text != NULL) {
                if (xmlStrcmp(propType, (const xmlChar*)"string") == 0) {
                    /*
                    memcpy(replaceText, (const*)text, atoi(propLen));
                    replace_string(replaceText, "\"", "\\\"");
                    */
                    sprintf(Buffer, "#%s  %s\t\t\t\t\"%s\"",
                            cur->name,
                            propName,
                            text);
                }
                else if (xmlStrcmp(propType, (const xmlChar*)"number") == 0) {
                    sprintf(Buffer, "#%s  %s\t\t\t\t(%s)",
                            cur->name,
                            propName,
                            text);
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
            xmlFree(propType);
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
            if (propType == NULL) {
                die("Type is NULL!!!\n");
            }
            else {
                xmlFree(propType);
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

 
