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
          { text: 'GPIO 与 LEDC', link: '/guide/03-gpio-ledc' },
          { text: 'I2C 与传感器', link: '/guide/04-i2c-sensor' },
          { text: 'Wi-Fi 与 HTTP', link: '/guide/05-wifi-http' },
          { text: 'FreeRTOS 深入理解', link: '/guide/06-freertos' },
          { text: 'AI 提示词工作流', link: '/guide/07-ai-prompts' },
          { text: '特殊章：ESP-Claw', link: '/guide/08-esp-claw' },
          { text: 'ADC 与 UART', link: '/guide/09-adc-uart' },
          { text: 'NVS、OTA 与工程化', link: '/guide/10-nvs-ota' },
          { text: '新方向与应用实例', link: '/guide/11-next-directions' }
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
