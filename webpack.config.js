const webpack = require("webpack");
const path = require("path");
const UglifyWebpackPlugin = require("uglifyjs-webpack-plugin");

const dir = p => path.resolve(__dirname, p);
module.exports = {
  entry: "./lib/js/src/web/browser.bs.js",
  output: {
    path: dir("./dist"),
    publicPath: "/",
    filename: "bundle.js"
  },
  module: {
    rules: [
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
