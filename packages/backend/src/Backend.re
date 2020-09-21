let app = Fastify.createServer(~logger=true);

Fastify.post(
  app,
  "/increment",
  (_req, res) => {
    let newValue = Dao.increment();

    ignore(FastifyAdditions.sendJson(res, Dao.toJson({value: newValue})));
  },
);

Fastify.get(
  app,
  "/value",
  (_req, res) => {
    let value = Dao.get();

    ignore(FastifyAdditions.sendJson(res, Dao.toJson({value: value})));
  },
);

FastifyAdditions.put(
  app,
  "/value",
  (req, res) => {
    let model = Dao.fromJson(req.body);

    ignore(Dao.set(model.value));

    ignore(FastifyAdditions.sendJson(res, Dao.toJson(model)));
  },
);

exception ListenException(Fastify.error);

let (let.await) = (p, fn) => Js.Promise.then_(fn, p);

let main = () => {
  let.await address =
    Js.Promise.make((~resolve, ~reject) =>
      Fastify.listen(app, 3000, result =>
        switch (result) {
        | Ok(x) =>
          Js.Console.log("listened!");
          resolve(. x);
        | Error(err) =>
          Js.Console.log("error!");
          reject(. ListenException(err));
        }
      )
    );

  Js.Console.log2("listened at", address);
  Js.Promise.resolve(app);
};

main()
|> Js.Promise.then_(app => FastifyAdditions.closeApp(app))
|> Js.Promise.catch(err => {
     Js.Console.log(err);
     Js.Promise.resolve();
   });
