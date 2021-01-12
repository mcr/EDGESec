module.exports = {
  title: "ManySecured Documentation",
  tagline: "NqurigingMind's ManySecured Documentation Website",
  url: "https://nqminds.com",
  baseUrl: "/ManySecured/",
  favicon: "images/safe-box.svg",
  organizationName: "nqminds", // Usually your GitHub org/user name.
  projectName: "ManySecured", // Usually your repo name.
  themeConfig: {
    prism: {
      additionalLanguages: ["protobuf"],
    },
    navbar: {
      title: "ManySecured",
      logo: {
        alt: "ManySecured Logo",
        src: "images/safe-box.svg",
      },
      links: [
        {to: "white-paper/common/0 - index", label: "Whitepaper", position: "left"},
        {
          to: "about",
          label: "About",
          position: "right",
        },
        {
          href: "https://github.com/nqminds/ManySecured",
          label: "GitHub",
          position: "right",
        },
      ],
    },
    footer: {
      style: "dark",
      links: [
        {
          title: "Docs",
          items: [
            {
              label: "Index",
              to: "/",
            },
            {
              label: "IoT Secure Hub Whitepaper",
              to: "white-paper/common/0 - index",
            },
          ],
        },
        {
          title: "Community",
          items: [
            {
              label: "Website",
              href: "https://nqmcyber.com",
            },
            {
              label: "Twitter",
              href: "https://twitter.com/nqminds",
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} NQMCyber LTD. Built with Docusaurus.`,
    },
  },
  plugins: [
    require.resolve("docusaurus-lunr-search"),
  ],
  presets: [
    [
      "@docusaurus/preset-classic",
      {
        docs: {
          routeBasePath: "/", // immediatly link to the docs page
          // It is recommended to set document id as docs home page (`docs/` path).
          homePageId: "secure-boot",
          sidebarPath: require.resolve("./sidebars.js"),
          // Please change this to your repo.
          editUrl:
            "https://github.com/nqminds/ManySecured/edit/master/docs/",
          showLastUpdateTime: true,
          remarkPlugins: [
            [require("remark-mermaid-dataurl"), {}],
          ],
        },
        theme: {
          customCss: require.resolve("./src/css/custom.css"),
        },
      },
    ],
  ],
};
