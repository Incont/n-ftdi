{
  "targets": [
    {
      "target_name": "FTD2XX",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "./src/FTD2XX.cc" ],
      "include_dirs": [
        "./src",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'conditions':
      [
        ['OS == "win"',
          {
            'include_dirs+':
            [
              './lib'
            ],
            'link_settings':
            {
              "conditions" :
              [
                ["target_arch=='ia32'",
                {
                  'libraries':
                  [
                   '-l<(module_root_dir)/lib/win/i386/ftd2xx.lib'
                  ]
                }
              ],
              ["target_arch=='x64'", {
                'libraries': [
                   '-l<(module_root_dir)/lib/win/amd64/ftd2xx.lib'
                ]
              }]
            ]
          }
        }],
        ['OS != "win"',
          {
            'include_dirs+': [
              '/usr/local/include',
              '/usr/local/include/libftd2xx/'
            ],
            'ldflags': [
              '-Wl,-Map=output.map',
            ],
            'link_settings': {
              'libraries': [
                '-lftd2xx'
              ]
            }
          }
        ]
      ],
    }
  ]
}
