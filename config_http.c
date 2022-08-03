#include "monitoring.h"

struct memory {
   char *response;
   size_t size;
 };

static size_t write_data(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;
 
    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)
        return 0;
 
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
    return realsize;
}
 
struct memory chunk = {0};

void config_http(char **str)
{
    CURL *curl = 0;;
    CURLcode result = 0;;
    const char *url = str[2];
    char *ct = 0;;
    long code = 0;;
    curl_off_t speed = 0;;
    curl_off_t connect = 0;;
    char *scheme = 0;
    long verifyresult = 0;;
    char *temp = 0;;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "init failed\n");
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, str[3]);
    result = curl_easy_perform(curl);
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Download problem is: %s\n", curl_easy_strerror(result));
    }
    else
    {
        printf("--------------------HTTP-----------------\n\n");
        fprintf(stdout, "###Successful request###.\n\n");
        printf("URL named: %s.\n\n", str[0]);
        printf("Request method: %s.\n\n", str[3]);
    //get infos
        curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
        curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME_T, &connect);
        curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD_T, &speed);
        curl_easy_getinfo(curl, CURLINFO_SSL_VERIFYRESULT, &verifyresult);
    //prints
        printf("Content :%s\n\n", ct);
        printf("Time to connect: %"//Time in microseconds from the start until the connection to the remote host
            CURL_FORMAT_CURL_OFF_T ".%06ld.\n\n", connect / 1000000,
            (long)(connect % 1000000));
        printf("Download speed: %" CURL_FORMAT_CURL_OFF_T " bytes/sec.\n\n", speed);
        printf("SSL connection is: %s.\n\n", verifyresult?
            "BAAAD":"fine");  
        temp = ft_itoa(curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code));
        if (ft_strncmp(temp, str[4], 4))
            printf("The response code is the same from the advertised on monitoring.db.\n\n");
        else
            printf("The response code is different from the advertised on monitoring.db, the code is: %ld, while in database is %s.\n\n", code, str[4]);
        if ((char *)curl_easy_getinfo(curl, CURLINFO_SCHEME, &scheme) == str[1])
            printf("The protocol is the same from the advertised on monitoring.db.\n\n");
        else
            printf("The protocol is different from the advertised on monitoring.db, the protocol is: %s.\n\n", scheme);
        printf("##### END #####\n\n");
    }
    curl_global_cleanup();
    curl_easy_cleanup (curl);
}
