require 'rubygems'
require 'sinatra'
get '/' do
  erb :index
end

get '/request_server' do
  server = TCPServer.new('127.0.0.1', 0)
  port = server.addr[1]
  server.close
  `docker run --cpu-shares=0 -d -p #{port}:8000 -t codebox`
  sleep 4
  redirect "http://54.175.171.124:#{port}"
end
