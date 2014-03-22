/*
 *    Copyright (C) 2014 Jules Colding <jcolding@gmail.com>.
 *
 *    All Rights Reserved.
 */

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     (1) Redistributions of source code must retain the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
    #include "ac_config.h"
#endif

#ifdef __linux__
    #include <unistd.h>
#endif
#include <stdlib.h>
#include "src/mastermind.h"
#include "cmdline/argopt.h"

static void
print_version(void)
{
	fprintf(stdout, "This is %s version %s\n", PACKAGE_NAME, PACKAGE_VERSION);
	fprintf(stdout, "Copyright (C) 2014 Jules Colding <jcolding@gmail.com>\n");
	fprintf(stdout, "All Rights Reserved\n");
}

int
main(int argc, char *argv[])
{
        // current argv index
        int index = 0;

        int c;
        char *parameter;
        struct option_t options[] = {
                {"version", "-version Prints the version of the server", NO_PARAM, NULL, 'v'},
                {"help", "-identity <IDENTITY> Identifies this server", NO_PARAM, NULL, 'h'},
                {0, 0, (enum need_param_t)0, 0, 0}
        };

        // get options
        while (1) {
                c = argopt(argc,
                           argv,
                           options,
                           &index,
                           &parameter);

                switch (c) {
                case ARGOPT_OPTION_FOUND :
                        break;
                case ARGOPT_AMBIGIOUS_OPTION :
                        argopt_completions(stderr,
                                           "Ambigious option found. Possible completions:",
                                           ++argv[index],
                                           options);
                        break;
                case ARGOPT_UNKNOWN_OPTION :
                        fprintf(stderr, "%d - Unknown option found:\t%s\n", __LINE__, argv[index]);
                        argopt_help(stdout,
                                    "Unknown option found",
                                    argv[0],
                                    options);
                        break;
                case ARGOPT_NOT_OPTION :
                        fprintf(stderr, "%d - Bad or malformed option found:\t%s\n", __LINE__, argv[index]);
                        argopt_help(stdout,
                                    "Bad or malformed option found",
                                    argv[0],
                                    options);
                        break;
                case ARGOPT_MISSING_PARAM :
                        fprintf(stderr, "%d - Option missing parameter:\t%s\n", __LINE__, argv[index]);
                        argopt_help(stdout,
                                    "Option missing parameter",
                                    argv[0],
                                    options);
                        break;
                case ARGOPT_DONE :
                        goto opt_done;
                case 'v':
                        print_version();
                        break;
                case 'h':
                        fprintf(stdout, "Start the gamne without any options and follow the instructions\n");
                        break;
                default:
                        fprintf(stderr, "?? get_option() returned character code 0%o ??\n", c);
                }
                if (parameter)
                        free(parameter);
                parameter = NULL;
        }

opt_done:
        if ((index) && (index < argc)) {
                fprintf(stderr, "non-option ARGV-elements: ");
                while (index < argc)
                        fprintf(stderr, "%s ", argv[index++]);
                fprintf(stderr, "\n");

                return EXIT_FAILURE;
        }

        exit(EXIT_SUCCESS);
}
