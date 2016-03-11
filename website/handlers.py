import os
import webapp2
import jinja2

#from google.appengine.ext import db


template_dir = os.path.join(os.path.dirname(__file__),'')
jinja_env = jinja2.Environment(loader = jinja2.FileSystemLoader(template_dir),autoescape = True)

class Handler(webapp2.RequestHandler):
    def write(self,*a,**kw):
        self.response.out.write(*a, **kw)

    def render_str(self, template, **params):
        t = jinja_env.get_template(template)
        return t.render(params)

    def render(self, template, **kw):
        self.write(self.render_str(template, **kw))

class MainPage(Handler):
    def get(self):
    	shop = self.request.get("shop")
    	if shop:
    		self.write(shop + " is open dude!!")
    	else:
    		self.render("index.html")

routes = [('/', MainPage), ]
# for GAE and paste server
app = webapp2.WSGIApplication( routes, debug=True)

def main():
    from paste import httpserver
    httpserver.serve(app, host='127.0.0.1', port='8080')

if __name__ == '__main__':
    main()
