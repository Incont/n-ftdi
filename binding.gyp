{
  "targets": [
    {
      "target_name": "N-FTD2XX",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ 
        "./src/N_FTD2XX.cc",
        "./src/ft_handler_wrapper.cc",
        "./src/ft_program_data_wrapper.cc",
        "./src/ft_create_device_info_list_op.cc",
        "./src/ft_get_device_info_detail_op.cc",
        "./src/ft_open_op.cc",
        "./src/ft_open_ex_op.cc",
        "./src/ft_close_op.cc",
        "./src/ft_set_data_characteristics_op.cc",
        "./src/ft_set_flow_control_op.cc",
        "./src/ft_set_baud_rate_op.cc",
        "./src/ft_get_device_info_op.cc",
        "./src/ft_ee_read_op.cc",
        "./src/ft_write_op.cc",
        "./src/ft_get_queue_status_op.cc",
        "./src/ft_get_status_op.cc",
         "./src/ft_read_op.cc"
      ],
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
