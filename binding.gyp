{
  "targets": [
    {
      "target_name": "N-FTD2XX",
      "cflags!": [
        "-fno-exceptions"
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
      "sources": [
        "./src/N_FTD2XX.cc",
        "./src/ft_program_data_wrapper.cc",
        "./src/ft_create_device_info_list_op.cc",
        "./src/ft_get_device_info_detail_op.cc",
        "./src/ft_open_op.cc",
        "./src/ft_open_ex_op.cc",
        "./src/ft_close_op.cc",
        "./src/ft_set_data_characteristics_op.cc",
        "./src/ft_set_flow_control_op.cc",
        "./src/ft_set_baud_rate_op.cc",
        "./src/ft_set_bit_mode_op.cc",
        "./src/ft_get_device_info_op.cc",
        "./src/ft_ee_read_op.cc",
        "./src/ft_write_op.cc",
        "./src/ft_get_queue_status_op.cc",
        "./src/ft_get_status_op.cc",
        "./src/ft_read_op.cc",
        "./src/ft_ex_program_device_description_op.cc",
        "./src/ft_get_vid_pid_op.cc",
        "./src/ft_cycle_port_op.cc",
        "./src/ft_ee_program_op.cc",
        "./src/ft_set_timeouts_op.cc",
        "./src/ft_set_latency_timer_op.cc",
        "./src/ft_purge_op.cc",
        "./src/ft_read_ee_op.cc",
        "./src/ft_write_ee_op.cc",
        "./src/ft_ee_ua_size_op.cc",
        "./src/ft_ee_ua_read_op.cc",
        "./src/ft_ee_ua_write_op.cc"
      ],
      "include_dirs": [
        "./src",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ],
      "include_dirs+": [
        "./lib"
      ],
      "conditions": [
        [
          "OS == 'win'",
          {
            "link_settings": {
              "conditions": [
                [
                  "target_arch=='ia32'",
                  {
                    "libraries": [
                      "-l<(module_root_dir)/lib/win/i386/ftd2xx.lib"
                    ]
                  }
                ],
                [
                  "target_arch=='x64'",
                  {
                    "libraries": [
                      "-l<(module_root_dir)/lib/win/amd64/ftd2xx.lib"
                    ]
                  }
                ]
              ]
            }
          }
        ],
        [
          "OS == 'mac'",
          {
            "ldflags": [
              "-Wl,-Map=output.map"
            ],
            "link_settings": {
              "libraries": [
                "<(module_root_dir)/lib/mac/libftd2xx.a"
              ]
            }
          }
        ],
        [
          "OS == 'linux'",
          {
            "link_settings": {
              "conditions": [
                [
                  "target_arch=='ia32'",
                  {
                    "libraries": [
                      "<(module_root_dir)/lib/linux/x86_32/libftd2xx.a"
                    ]
                  }
                ],
                [
                  "target_arch=='x64'",
                  {
                    "libraries": [
                      "<(module_root_dir)/lib/linux/x86_64/libftd2xx.a"
                    ]
                  }
                ]
              ]
            }
          }
        ]
      ],
    }
  ],
  "variables": {
    "openssl_fips": ""
  }
}