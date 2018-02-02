const webpack = require("webpack");
const path = require("path");

const dir = p => path.resolve(__dirname, p);
module.exports = {
  entry: "./lib/js/src/web/browser.bs.js",
  output: {
    path: dir("./build/assets"),
    publicPath: "/",
    filename: "bundle.js"
  },
  module: {
    loaders: [
      {
        test: /\.js$/,
        exclude: /node_modules/
      }
    ]
  },
  resolve: {
    extensions: [".js", ".bs.js"]
  }
};
