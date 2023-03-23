#include <json-c/json_object.h>
#include <json-c/json_types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <json-c/json.h>

#define BUFFERSIZE 128

#define url "https://intra.proekspert.ee/dragonquest/api/quests/85fc706b-ae95-462f-8dd3-703315e0bd21/task/data"
#define cmd "curl"


// Dependancies
// - json-c
// - curl

bool validateTag(const char *tag) {
	char *invalidTags[6] = {"aquatic", "frozen", "low G", "high G", "poor", "quarantined"};
	for (int i = 0; i < 6; i++) {
		if (strcmp(invalidTags[i], tag) == 0) {
			return false;
		}
	}
	return true;
}

bool hasTag(const char *tag) {
	char *validTags[5] = {"dangerous", "draconic", "fringe-world", "normal G", "rich"};
	for (int i = 0; i < 5; i++) {
		if (strcmp(validTags[i], tag) == 0) {
			break;
		}
		if (i == 4) {
			return false;
		}
	}
	return true;
}

bool check_tags(json_object *obj) {
	int valid_tags_found = 0;
	json_object *tags;
	// Access tags array
	json_bool hasKey = json_object_object_get_ex(obj, "tags", &tags);
	if (!hasKey) {
		printf("object does not have key tags\n");
		return false;
	} 
	if (json_object_get_type(tags) != json_type_array) {
		printf("tags not array\n");
		return false;
	}


	size_t len = json_object_array_length(tags);
	for (int i = 0; i < len; i++) {
	 	json_object *tag;
	 	tag = json_object_array_get_idx(tags, i);
	 	if (json_object_get_type(tag) != json_type_string) {
	 		return false;
	 	}
	 	if (!validateTag(json_object_get_string(tag))) {
	 		return false;
	 	}
		if (hasTag(json_object_get_string(tag))) {
			valid_tags_found++;
		}
	}
	if (valid_tags_found == 5) {
		return true;
	}
	return false;
}

void parse_json(char* json) {
	json_object *obj = json_tokener_parse(json);
	if (json_object_get_type(obj) != json_type_array) {
			printf("root not array\n");
			goto END;
	}

	size_t len = json_object_array_length(obj);
	for (int i = 0; i < len; i++) {
		json_object *arrObj;
		arrObj = json_object_array_get_idx(obj, i);
		if (json_object_get_type(arrObj) != json_type_object) {
			printf("array contains non object\n");
			goto END;
		}
		json_object *coords;
		json_bool hasKey = json_object_object_get_ex(arrObj, "planetaryCoordinates", &coords);
		if (!hasKey) {
			printf("object does not have key planetaryCoordinates\n");
			continue;
		}
		check_tags(arrObj);
		if (check_tags(arrObj)) {
			printf("potential candidate: %s\n", json_object_get_string(coords));
		}
	}
	END:
	json_object_put(obj);
	return;
}

int main() {
	unsigned long cmd_size = strlen(cmd) + strlen(url) + 2; // missing end characters
	char final_cmd[cmd_size];

	snprintf(final_cmd, cmd_size, "%s %s", cmd, url);
	printf("%s\n", final_cmd);


	FILE* f = popen(final_cmd, "r");
	if (f == NULL) {
		printf("failed to run curl, missing dependancy?\n");
	}

	char* json = malloc(BUFFERSIZE);
	char buffer[BUFFERSIZE];
	int i = 1;
	while (fgets(buffer, BUFFERSIZE, f) != NULL) {
		strcat(json, buffer);
		// printf("%s\n", buffer);
		i++;
		json = realloc(json, i * BUFFERSIZE);
		if (json == NULL) {
			printf("failed to allocate enough memory\n");
			pclose(f);
			return 1;
		}
	}
	pclose(f);
	// printf("%s", json);
	parse_json(json);
	free(json);
	return 0;
}
