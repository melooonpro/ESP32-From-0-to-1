import { defineConfig } from 'vitepress'

const base = process.env.VITEPRESS_BASE ?? '/'
const normalizedBase = base.endsWith('/') ? base : `${base}/`
const publicAsset = (asset: string) => `${normalizedBase}${asset.replace(/^\//, '')}`

export default defineConfig({
  lang: 'zh-CN',
  title: 'ESP32 从 0 到 1',
  description: '面向大学生的 ESP32、ESP-IDF、FreeRTOS 与 ESP-Claw 中文教程',
  base: normalizedBase,
  cleanUrls: true,
  lastUpdated: true,
  head: [
    ['link', { rel: 'icon', href: publicAsset('/official/espressif-logo.svg') }]
  ],
  themeConfig: {
    logo: '/official/espressif-logo.svg',
    siteTitle: 'ESP32 从 0 到 1',
    nav: [
      { text: '开始学习', link: '/guide/00-learning-map' },
      { text: '示例工程', link: '/reference/examples' },
      { text: '官方资料', link: '/reference/official-links' }
    ],
    sidebar: [
      {
        text: '从 0 到 1',
        items: [
          { text: '学习地图', link: '/guide/00-learning-map' },
          { text: '开发板与实验箱', link: '/guide/01-hardware-kit' },
          { text: 'Windows 环境搭建', link: '/guide/01-windows-setup' },
          { text: '第一个 Hello World', link: '/guide/02-hello-world' },
          { text: 'GPIO 数字输入输出', link: '/guide/03-gpio' },
          { text: 'LEDC PWM 输出', link: '/guide/04-ledc' },
          { text: 'I2C 总线扫描', link: '/guide/05-i2c' },
          { text: 'ADC 模拟采样', link: '/guide/06-adc' },
          { text: 'UART 串口通信', link: '/guide/07-uart' },
          { text: 'Wi-Fi 与 HTTP', link: '/guide/08-wifi-http' },
          { text: 'NVS 配置保存', link: '/guide/09-nvs' },
          { text: 'OTA 固件升级', link: '/guide/10-ota' },
          { text: 'FreeRTOS 深入理解', link: '/guide/11-freertos' },
          { text: 'AI 提示词工作流', link: '/guide/12-ai-prompts' },
          { text: '特殊章：ESP-Claw', link: '/guide/13-esp-claw' },
          { text: '应用案例', link: '/guide/14-applications' }
        ]
      },
      {
        text: '参考',
        items: [
          { text: '示例工程索引', link: '/reference/examples' },
          { text: '术语表', link: '/reference/glossary' },
          { text: '官方资料', link: '/reference/official-links' }
        ]
      }
    ],
    socialLinks: [
      { icon: 'github', link: 'https://github.com/melooonpro/ESP32-From-0-to-1' }
    ],
    footer: {
      message: '本教程使用中文编写，代码和命令保留必要英文。',
      copyright: '持续迭代中的 ESP32 学习资料'
    },
    search: {
      provider: 'local'
    }
  },
  markdown: {
    theme: {
      light: 'github-light',
      dark: 'github-dark'
    }
  }
})
