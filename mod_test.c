/* 
**  mod_test.c -- Apache sample test module
**  [Autogenerated via ``apxs -n test -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_test.c
**
**  Then activate it in Apache's apache2.conf file for instance
**  for the URL /test in as follows:
**
**    #   apache2.conf
**    LoadModule test_module modules/mod_test.so
**    <Location /test>
**    SetHandler test
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /test and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/test 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_test.c
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

/* The sample content handler */
static int test_handler(request_rec *r)
{
    if (strcmp(r->handler, "test")) {
        return DECLINED;
    }
    r->content_type = "text/html";      

    if (!r->header_only)
        ap_rputs("The sample page from mod_test.c\n", r);
    return OK;
}

static void test_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(test_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA test_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    test_register_hooks  /* register hooks                      */
};

