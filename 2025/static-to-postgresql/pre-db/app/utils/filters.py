"""
I didn't talk about this monstrosity in my blog post but this is how I 
write inline css that gets rendered with each blog post. I use the flatpages
meta property to store a style value that acts like a dictionary with key value
pairs. I use the flatten_yaml_to_css() function as a jinja2 filter to to take 
the resulting string and convert it to css.
"""

from datetime import datetime


def format_blog_time(time: datetime, format="%m-%d"):
    """
    Takes the datetime from flatpage YAML 
    meta data and returns it in the month-day 
    format for the "archives" blog posts
     """
    return time.strftime(format)


def make_spaces(level: int) -> str:
    spaces = (level * 4) * " "
    return spaces


def flatten_yaml_to_css(css_items: dict, level: int=0) -> str:
    """
    Returns a formatted css line from the flatpages 'style' YAML meta data.
    
    """
    print(css_items)    
    flatten_list = []
    for key, value in css_items.items():
        if isinstance(value, dict):
            flatten_list.append(make_spaces(level - 1) + key + " {\n")
            flatten_list.append(flatten_yaml_to_css(value, level + 1))
            flatten_list.append(make_spaces(level - 1) + "}\n")
        else:
            next_row = make_spaces(level) + key + ": " + value + ";\n"
            flatten_list.append(next_row)
    return "".join(flatten_list)



FILTERS = [format_blog_time, flatten_yaml_to_css]


def init_app(app):
    for func in FILTERS:
        app.add_template_filter(func)