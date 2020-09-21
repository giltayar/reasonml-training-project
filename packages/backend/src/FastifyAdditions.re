open Fastify;

[@bs.send] external closeApp: server => Js.Promise.t(unit) = "close";
[@bs.send]
external sendJson: (reply, Js.Json.t) => Js.Promise.t(unit) = "send";

[@bs.send] external put: (server, string, postHandler) => unit = "put";
