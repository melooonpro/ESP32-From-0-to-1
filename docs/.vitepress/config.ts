import { defineConfig } from 'vitepress'

const base = process.env.VITEPRESS_BASE ?? '/'
const normalizedBase = base.endsWith('/') ? base : `${base}/`
const publicAsset = (asset: string) => `${normalizedBase}${asset.replace(/^\//, '')}`
const siteUrl = (process.env.VITEPRESS_SITE_URL ?? 'https://melooon.top').replace(/\/$/, '')
const siteTitle = 'ESP32 从 0 到 1'
const siteDescription = '面向大学生的 ESP32、ESP-IDF、FreeRTOS 与 ESP-Claw 中文教程'
const sitePreviewImage = `${siteUrl}/official/esp-claw-logo.jpg`

export default defineConfig({
  lang: 'zh-CN',
  title: siteTitle,
  description: siteDescription,
  base: normalizedBase,
  cleanUrls: true,
  lastUpdated: true,
  head: [
    ['link', { rel: 'icon', href: publicAsset('/official/espressif-logo.svg') }],
    ['meta', { property: 'og:type', content: 'website' }],
    ['meta', { property: 'og:site_name', content: siteTitle }],
    ['meta', { property: 'og:title', content: siteTitle }],
    ['meta', { property: 'og:description', content: siteDescription }],
    ['meta', { property: 'og:url', content: siteUrl }],
    ['meta', { property: 'og:image', content: sitePreviewImage }],
    ['meta', { property: 'og:image:secure_url', content: sitePreviewImage }],
    ['meta', { property: 'og:image:type', content: 'image/jpeg' }],
    ['meta', { property: 'og:image:width', content: '1816' }],
    ['meta', { property: 'og:image:height', content: '825' }],
    ['meta', { property: 'og:image:alt', content: 'ESP-Claw logo' }],
    ['meta', { name: 'twitter:card', content: 'summary_large_image' }],
    ['meta', { name: 'twitter:title', content: siteTitle }],
    ['meta', { name: 'twitter:description', content: siteDescription }],
    ['meta', { name: 'twitter:image', content: sitePreviewImage }]
  ],
  themeConfig: {
    logo: '/official/espressif-logo.svg',
    siteTitle,
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
          { text: 'Touch 触摸感应', link: '/guide/08-touch' },
          { text: 'Wi-Fi 与 HTTP', link: '/guide/09-wifi-http' },
          { text: 'NVS 配置保存', link: '/guide/10-nvs' },
          { text: 'OTA 固件升级', link: '/guide/11-ota' },
          { text: 'FreeRTOS 深入理解', link: '/guide/12-freertos' },
          { text: 'AI 提示词工作流', link: '/guide/13-ai-prompts' },
          { text: '特殊章：ESP-Claw', link: '/guide/14-esp-claw' },
          { text: '应用案例', link: '/guide/15-applications' }
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
