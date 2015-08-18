import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
	def get(self):
		param1 = self.get_argument("param1","default")
		param2 = self.get_argument("param2","default2")
		##print(param1)
		res = {"get:":param1,"get2:":param2}
		self.write(res)

class FuckHandler(tornado.web.RequestHandler):
	def get(self):
		##param1 = self.get_argument("param1","default")
		##print(param1)
		##res = {"get:":param1}
		self.write("")

application = tornado.web.Application([
	(r"/nima", MainHandler),
	(r"/",FuckHandler),
])

if __name__ == "__main__":
    application.listen(8888)
    tornado.ioloop.IOLoop.current().start()
