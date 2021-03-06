const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const ExtractCssChunks = require("extract-css-chunks-webpack-plugin");

const appDirectory = path.resolve(__dirname);
const ASSET_PATH = process.env.ASSET_PATH || '/';

module.exports = {
  entry: path.resolve(appDirectory, 'lib/js/src/index.js'),
  output: {
    chunkFilename: "[name].[chunkhash:4].js",
    filename: "[name].[chunkhash:4].js",
    path: path.resolve(appDirectory, 'dist'),
    publicPath: ASSET_PATH,
  },
  devServer: {
    port: 3000,
    historyApiFallback: true,
  },
  devtool: 'source-map',
  module: {
    rules: [{
      test: /\.svg$/,
      loader: 'svg-url-loader',
      options: {
        limit: 10 * 1024,
        noquotes: true,
      },
    },
    {
      test: /\.css$/,
      use: [
        ExtractCssChunks.loader,
        "css-loader"
      ]
    }],
  },
  optimization: {
    splitChunks: {
      chunks: 'all'
    },
    nodeEnv: 'production',
    minimize: true,
  },
  plugins: [
    new webpack.DefinePlugin({
      'process.env.NODE_ENV': JSON.stringify(process.env.NODE_ENV || 'development'),
      __DEV__: process.env.NODE_ENV !== 'production' || true,
    }),
    new ExtractCssChunks({
        filename: "[name].css",
        chunkFilename: "[name].[contenthash].css",
        hot: true
    }),
    new HtmlWebpackPlugin({
      template: 'public/index.html',
    }),
  ],
};
