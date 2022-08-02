#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include "monitoring.h"

struct memory {
   char *response;
   size_t size;
 };

size_t write_data(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;
 
    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)
        return 0;  /* out of memory! */
 
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
 
    return realsize;
}
 
struct memory chunk = {0};

void config_http(char **str)
{
    CURL *curl;
    CURLcode result;
    const char *url = str[2];
    char *ct;
    long code;
    curl_off_t speed;
    curl_off_t connect;
    char *scheme = NULL;
    long verifyresult;
    char *temp;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "init failed\n");
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
/* send all data to this function  */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
/* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, str[3]);  /* use um GET para buscar isso */
    result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        fprintf(stderr, "Download problem is: %s\n", curl_easy_strerror(result));
    }
    else
    {
        printf("-----------HTTP----------\n\n");
        fprintf(stdout, "Successful request.\n\n");
        printf("Let's start monitoring the URL named as: %s.\n\n", str[0]);
        temp = ft_itoa(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code));
        if (ft_strncmp(temp, str[4], 4))
            printf("The response code is the same from the advertised on monitoring.db.\n\n");
        else
            printf("The response code is different from the advertised on monitoring.db, the code is: %ld, while in database is %s.\n\n", code, str[4]);
        if ((char *)curl_easy_getinfo(curl, CURLINFO_SCHEME, &scheme) == str[1])
            printf("The protocol is the same from the advertised on monitoring.db.\n\n");
        else
            printf("The protocol is different from the advertised on monitoring.db, the protocol is: %s.\n\n", scheme);

        curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
        curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME_T, &connect);
        curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD_T, &speed);
        curl_easy_getinfo(curl, CURLINFO_SSL_VERIFYRESULT, &verifyresult);
    //prints
        printf("The content of the URL is :%s\n\n", ct);
        printf("Time in microseconds from the start until the connection to the remote host is: %"
            CURL_FORMAT_CURL_OFF_T ".%06ld\n\n", connect / 1000000,
            (long)(connect % 1000000));
        printf("Download speed is %" CURL_FORMAT_CURL_OFF_T " bytes/sec\n\n", speed);
        printf("The peer verification said the SSL is %s\n\n", verifyresult?
            "BAAAD":"fine");  
        printf("End of monitoring by protocol %s.\n\n", str[1]);
        printf("##### END #####\n\n");
    }
    
    curl_global_cleanup();
    curl_easy_cleanup (curl);
}
