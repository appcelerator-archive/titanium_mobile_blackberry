var CLASSNAME = 'todo';

function Todo(title) {
  this.id = null;
  this.title = title;
  this.completed = false;
}

Todo.prototype.markCompleted = function(complete, cb) {
  this.save({completed: complete}, cb);
}

Todo.prototype.isNew = function() {
  return this.id == null;
}

Todo.prototype.save = function(cb) {
  var self = this;
  (this.isNew() ? Cloud.Objects.create : Cloud.Objects.update)({
    classname: CLASSNAME,
    id: this.id,
    fields: {
      title: this.title,
      completed: this.completed
    }
  }, function(e) {
    if (e.success) {
      self.id = e[CLASSNAME].id;
    }
    cb((e.error && e.message) || null);
  });
}

Todo.fetch = function(cb) {
  Cloud.Objects.query({
    classname: CLASSNAME,
    limit: 100
  }, function(e) {
    cb((e.error && e.message) || null, e[CLASSNAME]);
  });
}

module.exports = Todo;
